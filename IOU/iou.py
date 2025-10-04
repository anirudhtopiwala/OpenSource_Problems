import numpy as np

def iou(
    box1_top_left: np.ndarray,
    box1_bottom_right: np.ndarray,
    box2_top_left: np.ndarray,
    box2_bottom_right: np.ndarray,
) -> np.ndarray:
    """
    Computes pairwise IoU between two sets of axis-aligned bounding boxes.

    Args:
        box1_top_left (N, 2): Top-left corners of N predicted boxes.
        box1_bottom_right (N, 2): Bottom-right corners of N predicted boxes.
        box2_top_left (M, 2): Top-left corners of M ground-truth boxes.
        box2_bottom_right (M, 2): Bottom-right corners of M ground-truth boxes.

    Returns:
        iou_matrix (N, M): IoU between each predicted and ground-truth box.
    """

    # Expand dimensions for broadcasting: (N, 1, 2) vs (1, M, 2)
    box1_top_left = box1_top_left[:, None, :]
    box1_bottom_right = box1_bottom_right[:, None, :]
    box2_top_left = box2_top_left[None, :, :]
    box2_bottom_right = box2_bottom_right[None, :, :]

    # Compute intersection box
    intersect_top_left = np.maximum(box1_top_left, box2_top_left)  # (N, M, 2)
    intersect_bottom_right = np.minimum(
        box1_bottom_right, box2_bottom_right
    )  # (N, M, 2)

    # Width and height of intersection region, clipped to non-negative values
    intersect_wh = np.clip(
        intersect_bottom_right - intersect_top_left, a_min=0, a_max=None
    )  # (N, M, 2)
    intersect_area = np.prod(intersect_wh, axis=2)  # (N, M)

    # Compute areas of each box
    box1_area = np.prod(box1_bottom_right - box1_top_left, axis=2)  # (N, 1)
    box2_area = np.prod(box2_bottom_right - box2_top_left, axis=2)  # (1, M)

    # Compute union area
    union_area = box1_area + box2_area - intersect_area  # (N, M)

    # Avoid division by zero
    iou_matrix = np.where(union_area == 0, 0.0, intersect_area / union_area)

    return iou_matrix


# Image dimensions
H = W = 512

# Number of predicted and ground-truth boxes
N = 20
M = 30

# Generate N predicted boxes and M ground-truth boxes
# Format: [top-left, bottom-right] with shape (N, 2) and (M, 2)
predicted_top_left = np.random.randint(0, H // 2, size=(N, 2))
predicted_bottom_right = np.random.randint(H // 2, H, size=(N, 2))

gt_top_left = np.random.randint(0, H // 2, size=(M, 2))
gt_bottom_right = np.random.randint(H // 2, H, size=(M, 2))


# Compute pairwise IoUs
iou_matrix = iou(
    predicted_top_left, predicted_bottom_right, gt_top_left, gt_bottom_right
)

# Print results
print("IoU shape:", iou_matrix.shape)  # Expected: (20, 30)
print("IoU values:\n", iou_matrix)
