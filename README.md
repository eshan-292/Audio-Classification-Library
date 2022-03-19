# COP290

## Model

A deep neural network (DNN) inference for classifying across 12 audio keywords (silence, unknown, yes, no, up, down, left, right, on, off, stop, go) implemented as an API.
The DNN comprises of FC1 [250x144] -> RELU -> FC2 [144x144] -> RELU -> FC3 [144X144] -> RELU -> FC4 [144x12] -> softmax

Given feature vector  of a 1 second audio clip, the API returns the top 3 keywords with highest softmax probabilities.
