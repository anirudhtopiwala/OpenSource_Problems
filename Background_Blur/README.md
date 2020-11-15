# BlurTheBackground
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---
## Overview
Background blurring has become the new hot feature everybody wants with the onset of WFH because of the pandemic. I was really impressed by the way google meet was able to blur the background so well. So in this project I tried to figure out how they might be doing this on the backend.

I came up with two possible methods, one is a bit straight forward using DeepLabv3 segmentation network to detect human detected pixels and then use this mask to blur the background, the other one is a bit out there. I used a MiDas monocular depth estimation network to predict the relative depth of an object in front of the camera. I then use that to create a mask for the object which is nearest to the camera and then blur the background.

I have used pre trained models for both the methods from torch hub and summarized a comparison between both the methods in my medium blog post ["Live Background Blur..How does it work?"](https://medium.com/@topiwala.anirudh/4c0491bcf2fa?source=friends_link&sk=2a0e3400d5b9de03715db6757e94d144).

## Results !!!

Background blur using MiDas.
<p align="center">
<img src="https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Background_Blur/assests/midas_combine.gif">
</p>


Background blur using DeepLabV3.
<p align="center">
<img src="https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Background_Blur/assests/deeplab_combine.gif">
</p>

Comparing Background Blur of MiDaS with that from Google meet.
<p align="center">
<img src="https://github.com/anirudhtopiwala/OpenSource_Problems/blob/master/Background_Blur/assests/meet_midas.gif">
</p>


## Dependencies
To run this program you need to have the following installed on your system:
```
$pip3 install opencv-python
$pip3 install torch
$pip3 install torchvision
```
This code has been tested with python3.6, torch 1.6.0, torchvision 0.7.0 and CUDA 10.1.

## Running the code
You can run live background blur using two methods.

To run using the MiDaS model:
```
$ python3 background_blur.py -m midas
```

To run using the DeepLabv3 model:
```
$ python3 background_blur.py -m deeplabv3
```
