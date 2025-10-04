"""
Inputs: [B, H, W, E] -> [B, L, E]
Outputs: [B, L, W]

"""

import torch
from torch import nn

MAX_LEN_POS = 128 * 128


class TransformerEncoder(nn.Module):
    def __init__(self, num_layers, num_heads, embeddng_dim, dropout=0.1):
        super().__init__()

        # Add positional embeddings at encoder level
        self.pos_embed = PositionalEmbeddings(embeddng_dim)
        self.dropout = nn.Dropout(dropout)

        self.enc_modules = nn.ModuleList()
        for _ in range(num_layers):
            self.enc_modules.append(EncoderBlock(num_heads, embeddng_dim, dropout))

    def forward(self, x, mask=None):
        # Add positional embeddings once at the beginning
        x = x + self.pos_embed(x)
        x = self.dropout(x)

        for layer in self.enc_modules:
            x = layer(x, mask)
        return x


class EncoderBlock(nn.Module):
    def __init__(self, num_heads, embeddng_dim, dropout=0.1):
        super().__init__()
        self.mha = MHA(num_heads, embeddng_dim, dropout)
        self.ffd = FeedForward(embeddng_dim, dropout)
        self.norm1 = nn.LayerNorm(embeddng_dim)
        self.norm2 = nn.LayerNorm(embeddng_dim)
        self.dropout = nn.Dropout(dropout)

    def forward(self, x, mask=None):
        """
        x: [B, L, E]
        Pre-norm architecture with residual connections
        """
        # Multi-head attention with residual connection
        residual = x
        x = self.norm1(x)
        x = self.mha(x, mask)
        x = self.dropout(x) + residual

        # Feed forward with residual connection
        residual = x
        x = self.norm2(x)
        x = self.ffd(x)
        x = self.dropout(x) + residual
        return x


class PositionalEmbeddings(nn.Module):
    def __init__(self, embedding_dim, max_len=5000):
        super().__init__()
        self.embedding_dim = embedding_dim

        # Create positional encoding matrix
        pe = torch.zeros(max_len, embedding_dim)
        position = torch.arange(0, max_len, dtype=torch.float).unsqueeze(1)

        # Create div_term for the sinusoidal pattern
        div_term = torch.exp(
            torch.arange(0, embedding_dim, 2).float()
            * (-torch.log(torch.tensor(10000.0)) / embedding_dim)
        )

        # Apply sine to even indices
        pe[:, 0::2] = torch.sin(position * div_term)
        # Apply cosine to odd indices
        pe[:, 1::2] = torch.cos(position * div_term)

        # Register as buffer (not a parameter, but part of state)
        self.register_buffer("pe", pe)

    def forward(self, x):
        """
        x: [B, L, E]
        Returns: [B, L, E] positional embeddings
        """
        B, L, _ = x.shape
        # Return positional embeddings for sequence length L
        return self.pe[:L].unsqueeze(0).expand(B, -1, -1)


class MHA(nn.Module):
    def __init__(self, num_heads, embeddng_dim, dropout=0.1):
        super().__init__()
        self.embedding_dim = embeddng_dim
        self.heads = num_heads
        assert embeddng_dim % num_heads == 0
        self.dim_per_head = embeddng_dim // num_heads
        self.query = nn.Linear(embeddng_dim, embeddng_dim, bias=False)
        self.key = nn.Linear(embeddng_dim, embeddng_dim, bias=False)
        self.value = nn.Linear(embeddng_dim, embeddng_dim, bias=False)
        self.proj = nn.Linear(embeddng_dim, embeddng_dim, bias=False)
        self.dropout = nn.Dropout(dropout)

        # Correct scaling factor
        self.scale = 1.0 / (self.dim_per_head**0.5)

    def _resize(self, x):
        B, L, D = x.shape
        x = x.view(B, L, self.heads, self.dim_per_head)
        return x.permute(0, 2, 1, 3)  # [B, H, L, D_head]

    def forward(self, x, mask=None):
        q = self.query(x)  # [B, L, D] -> [B, L, D]
        k = self.key(x)  # [B, L, D] -> [B, L, D]
        v = self.value(x)  # [B, L, D] -> [B, L, D]

        q, k, v = self._resize(q), self._resize(k), self._resize(v)

        # Attention computation
        score = self.scale * q @ k.transpose(-2, -1)  # [B, H, L, L]

        # Apply mask if provided
        if mask is not None:
            score = score.masked_fill(mask, float("-inf"))

        soft_score = torch.softmax(score, dim=-1)  # [B, H, L, L]
        soft_score = self.dropout(soft_score)

        final = soft_score @ v  # [B, H, L, D_head]

        # Reshape back to [B, L, D]
        final = final.permute(0, 2, 1, 3).contiguous().flatten(start_dim=2)
        return self.proj(final)


class FeedForward(nn.Module):
    def __init__(self, embeddng_dim, dropout=0.1):
        super().__init__()
        # Standard transformer uses 4x expansion ratio
        hidden_dim = 4 * embeddng_dim
        self.fc1 = nn.Linear(embeddng_dim, hidden_dim)
        self.non_linearity = nn.GELU()
        self.fc2 = nn.Linear(hidden_dim, embeddng_dim)
        self.dropout = nn.Dropout(dropout)

    def forward(self, x):
        x = self.fc1(x)
        x = self.non_linearity(x)
        x = self.dropout(x)
        x = self.fc2(x)
        return x


class OptimizedTransformerEncoder(TransformerEncoder):
    """Optimized version with additional features for better performance"""

    def __init__(
        self,
        num_layers,
        num_heads,
        embedding_dim,
        dropout=0.1,
        use_flash_attention=False,
        gradient_checkpointing=False,
    ):
        super().__init__(num_layers, num_heads, embedding_dim, dropout)

        self.use_flash_attention = use_flash_attention
        self.gradient_checkpointing = gradient_checkpointing

        # Weight initialization for better training stability
        self._init_weights()

    def _init_weights(self):
        """Initialize weights using Xavier/Glorot initialization"""
        for module in self.modules():
            if isinstance(module, nn.Linear):
                torch.nn.init.xavier_uniform_(module.weight)
                if module.bias is not None:
                    torch.nn.init.zeros_(module.bias)
            elif isinstance(module, nn.LayerNorm):
                torch.nn.init.ones_(module.weight)
                torch.nn.init.zeros_(module.bias)

    def forward(self, x, mask=None):
        x = x + self.pos_embed(x)
        x = self.dropout(x)

        for layer in self.enc_modules:
            if self.gradient_checkpointing and self.training:
                # Use gradient checkpointing to save memory
                x = torch.utils.checkpoint.checkpoint(layer, x, mask)
            else:
                x = layer(x, mask)
        return x


class FlashMHA(nn.Module):
    """Memory-efficient attention implementation"""

    def __init__(self, num_heads, embedding_dim, dropout=0.1):
        super().__init__()
        self.embedding_dim = embedding_dim
        self.heads = num_heads
        assert embedding_dim % num_heads == 0
        self.dim_per_head = embedding_dim // num_heads

        # Use single linear layer for efficiency
        self.qkv = nn.Linear(embedding_dim, 3 * embedding_dim, bias=False)
        self.proj = nn.Linear(embedding_dim, embedding_dim, bias=False)
        self.dropout = nn.Dropout(dropout)

        self.scale = 1.0 / (self.dim_per_head**0.5)

    def forward(self, x, mask=None):
        B, L, D = x.shape

        # Compute Q, K, V in one go
        qkv = self.qkv(x).reshape(B, L, 3, self.heads, self.dim_per_head)
        qkv = qkv.permute(2, 0, 3, 1, 4)  # [3, B, H, L, D_head]
        q, k, v = qkv[0], qkv[1], qkv[2]

        # Scaled dot-product attention with memory optimization
        if hasattr(torch.nn.functional, "scaled_dot_product_attention"):
            # Use PyTorch's optimized attention (available in PyTorch 2.0+)
            attn_mask = mask.squeeze() if mask is not None else None
            out = torch.nn.functional.scaled_dot_product_attention(
                q,
                k,
                v,
                attn_mask=attn_mask,
                dropout_p=self.dropout.p if self.training else 0.0,
            )
        else:
            # Fallback to manual implementation
            scores = torch.matmul(q, k.transpose(-2, -1)) * self.scale

            if mask is not None:
                scores = scores.masked_fill(mask, float("-inf"))

            attn_weights = torch.softmax(scores, dim=-1)
            attn_weights = self.dropout(attn_weights)
            out = torch.matmul(attn_weights, v)

        # Reshape and project
        out = out.transpose(1, 2).contiguous().view(B, L, D)
        return self.proj(out)


def create_distributed_model(strategy="data", world_size=1, rank=0):
    """Factory function to create distributed models"""
    if strategy == "data" and world_size > 1:
        from torch.nn.parallel import DistributedDataParallel as DDP

        model = OptimizedTransformerEncoder(
            num_layers=12, num_heads=8, embedding_dim=512, gradient_checkpointing=True
        )
        model = DDP(model, device_ids=[rank])
        return model
    else:
        return OptimizedTransformerEncoder(
            num_layers=6, num_heads=8, embedding_dim=512, dropout=0.1
        )


# Example usage with proper parameters
model = OptimizedTransformerEncoder(
    num_layers=6, num_heads=8, embedding_dim=512, dropout=0.1
)

# Test the model
if __name__ == "__main__":
    # Create sample input [batch_size, sequence_length, embedding_dim]
    batch_size, seq_len, emb_dim = 2, 10, 512
    x = torch.randn(batch_size, seq_len, emb_dim)

    # Optional attention mask (e.g., padding mask)
    # mask = torch.zeros(batch_size, 1, 1, seq_len).bool()  # No masking

    output = model(x)
    print(f"Input shape: {x.shape}")
    print(f"Output shape: {output.shape}")

    # Test distributed model creation
    distributed_model = create_distributed_model("data", 1, 0)
    dist_output = distributed_model(x)
    print(f"Distributed output shape: {dist_output.shape}")
