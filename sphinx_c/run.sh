gcc -o testing_mic testing_mic.c -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`

./testing_mic -inmic yes -dict model/cmudict-en-us.dict -hmm model/cmusphinx-en-us-8khz-5.2
