# K-Means

import numpy as np
import matplotlib.pyplot as plt


def get_labels(centers, data):
    diff = centers[:, np.newaxis, :] - data[np.newaxis, :, :]  # [K, N, D]
    dist = np.linalg.norm(diff, axis=-1)  # [k, N]
    labels = np.argmin(dist, axis=0)
    return labels, dist


def k_means(data, k, num_episodes):
    centers = data[np.random.randint(0, data.shape[0], k)]  # [k, D]
    for _ in range(num_episodes):
        labels, _ = get_labels(centers, data)
        k_arr = np.arange(0, k)  # [k, 1]
        mask = k_arr[:, np.newaxis] == labels[np.newaxis, :]  # [k,N]
        centers = np.matmul(mask, data) / (np.sum(mask, axis=1)[:, np.newaxis] + 1e-5)

    labels, dist = get_labels(centers, data)
    min_distanes = np.sum(np.min(dist, axis=0) ** 2)
    return labels, min_distanes, centers


def main():
    N = 1000
    D = 3
    data = np.random.rand(N, D)
    err_list = []
    centers_list = []
    for i in range(1, 30):
        _, error, centers = k_means(data, i, 1000)
        err_list.append(error)
        centers_list.append(centers)
        print(f"Value of k = {i} with error={error}")

    # Using the second derivative to find the K.
    error_arr = np.array(err_list)
    diff = error_arr[:-1] - error_arr[1:]
    # second derivative.
    # Find the elbow point where the error reduction slows down significantly.
    threshold = 0.1 * (error_arr[0] - error_arr[-1])  # 10% of the total error reduction
    elbow_k = np.argmax(diff < threshold) + 1

    print(f"Optimal k value: {elbow_k} with error: {error_arr[elbow_k]}")
    labels, _ = get_labels(centers_list[elbow_k], data)

    # 3D scatter plot
    fig = plt.figure(figsize=(10, 4))
    # Original data
    ax1 = fig.add_subplot(131, projection="3d")
    ax1.scatter(data[:, 0], data[:, 1], data[:, 2])
    ax1.set_title("Original Data")
    ax1.set_xlabel("X")
    ax1.set_ylabel("Y")
    ax1.set_zlabel("Z")

    ax2 = fig.add_subplot(132, projection="3d")
    ax2.scatter(data[:, 0], data[:, 1], data[:, 2], c=labels, cmap="rainbow")
    ax2.set_title("Clustered Data")
    ax2.set_xlabel("X")
    ax2.set_ylabel("Y")
    ax2.set_zlabel("Z")

    ax3 = fig.add_subplot(133)
    ax3.plot(list(range(len(err_list))), err_list)
    plt.show()


if __name__ == "__main__":
    main()
