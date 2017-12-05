#! /usr/bin/env python
# -*- coding: utf-8 -*-

#https://github.com/fchollet/keras/blob/master/examples/lstm_text_generation.py

from __future__ import print_function
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.layers import LSTM
from keras.optimizers import RMSprop
from keras.utils import get_file
import numpy as np
import random
import sys
import argparse

model_url = 'https://github.com/Vzzzz/TestingTasks/raw/master/Azoft/LSTM_text_gen/model.ckpt'
text_url = 'https://raw.githubusercontent.com/Vzzzz/TestingTasks/master/Azoft/LSTM_text_gen/R%26D%20article_texts.txt'

#"Hyperparams"
sequence_length = 40
step = 3

def build_model(seq_len, total_chars):
    model = Sequential()
    model.add(LSTM(128, input_shape=(seq_len, total_chars)))
    model.add(Dense(total_chars))
    model.add(Activation('softmax'))
    optimizer = RMSprop(lr=0.01)
    model.compile(loss='categorical_crossentropy', optimizer=optimizer)
    return model

def sample(preds, temperature=1.0):
    # helper function to sample an index from a probability array
    preds = np.asarray(preds).astype('float64')
    preds = np.log(preds) / temperature
    exp_preds = np.exp(preds)
    preds = exp_preds / np.sum(exp_preds)
    probas = np.random.multinomial(1, preds, 1)
    return np.argmax(probas)

def gen_text(model, length, text, start_index, chars, diversity=0.2):
    char_indices = dict((c, i) for i, c in enumerate(chars))
    indices_char = dict((i, c) for i, c in enumerate(chars))
    generated = ''
    sentence = text[start_index: start_index + sequence_length]
    generated += sentence
    print('Generating with seed: "' + sentence + '"')
    for i in range(length):
        x_pred = np.zeros((1, sequence_length, len(chars)))
        for t, char in enumerate(sentence):
            x_pred[0, t, char_indices[char]] = 1.

        preds = model.predict(x_pred, verbose=0)[0]
        next_index = sample(preds, diversity)
        next_char = indices_char[next_index]

        generated += next_char
        sentence = sentence[1:] + next_char
    return generated


def main(args):
    if args.model is None:
        model_path = get_file('model.ckpt', model_url)
    else:
        model_path = args.model

    if args.text is None:
        text_path = get_file('R&D article_texts.txt', text_url)
    else:
        text_path = args.text

    text = open(text_path).read().lower()
    chars = sorted(list(set(text)))

    model = build_model(sequence_length, len(chars))
    model.load_weights(model_path)

    for i in range(10):
        start_index = random.randint(0, len(text) - sequence_length - 1)
        sentence = gen_text(model, 200, text, start_index, chars)
        print(sentence)
        print()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--model', help='path to model checkpoint file', default=None)
    parser.add_argument('--text', help='path to training text file', default=None)
    args = parser.parse_args()
    main(args)
