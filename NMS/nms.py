import torch
from dataclasses import dataclass
import numpy as np


@dataclass
class Box:
    """Represent the bottom left and top right coordinates of a box."""
    bottom_left_x: float = 0
    bottom_left_y: float = 0
    top_right_x: float = 0
    top_right_y: float = 0

    def area(self) -> float:
        return max(0, self.top_right_x - self.bottom_left_x) * max(
            0, self.top_right_y - self.bottom_left_y)


def iou(box_1: Box, box_2: Box) -> float:
    """Returns intersection over union between the two boxes."""
    intersecting_box = Box()
    intersecting_box.bottom_left_x = max(box_1.bottom_left_x,
                                         box_2.bottom_left_x)
    intersecting_box.bottom_left_y = max(box_1.bottom_left_y,
                                         box_2.bottom_left_y)
    intersecting_box.top_right_x = min(box_1.top_right_x, box_2.top_right_x)
    intersecting_box.top_right_y = min(box_1.top_right_y, box_2.top_right_y)

    return intersecting_box.area() / (box_1.area() + box_2.area() -
                                      intersecting_box.area())


def nms_pytorch(boxes: torch.Tensor, thresh_iou: float):
    """Apply non-maximum suppression to avoid detecting too many overlapping bounding boxes for a given object.

    Args:
        boxes: (tensor) The location preds for the image along with the class predscores, Shape: [num_boxes,5].
        thresh_iou: (float) The overlap thresh for suppressing unnecessary boxes.
    Returns:
        A list of filtered boxes, Shape: [ , 5]
    """
    scores = boxes[:, 4]
    to_keep_indices = []
    areas = (boxes[:, 2] - boxes[:, 0]) * (boxes[:, 3] - boxes[:, 1])
    # Sort boxes by score
    sorted_box_indices = scores.argsort()

    while len(sorted_box_indices) > 0:
        idx = sorted_box_indices[-1]
        to_keep_indices.append(idx)
        sorted_box_indices = sorted_box_indices[:-1]
        other_boxes = torch.index_select(boxes,
                                         dim=0,
                                         index=sorted_box_indices)
        other_box_areas = torch.index_select(areas,
                                             dim=0,
                                             index=sorted_box_indices)
        w = torch.minimum(boxes[idx][2], other_boxes[:, 2]) - torch.maximum(
            boxes[idx][0], other_boxes[:, 0])
        h = torch.minimum(boxes[idx][3], other_boxes[:, 3]) - torch.maximum(
            boxes[idx][1], other_boxes[:, 1])
        w = torch.clamp(w, min=0)
        h = torch.clamp(h, min=0)

        intersection_area = w * h
        mask = (
            intersection_area /
            (other_box_areas + areas[idx] - intersection_area)) < thresh_iou
        sorted_box_indices = sorted_box_indices[mask]

    return boxes[to_keep_indices, :]


def main():
    # box_1 = Box(1, 1, 2, 2)
    # box_2 = Box(1, 1, 1.5, 1.5)
    # print(iou(box_1, box_2))

    boxes = torch.Tensor([[1, 1, 3, 3, 0.95], [1, 1, 3, 4, 0.93],
                          [1, 0.9, 3.6, 3, 0.98], [1, 0.9, 3.5, 3, 0.97]])

    boxes = nms_pytorch(boxes, 0.5)
    print(boxes)


if __name__ == "__main__":
    main()
