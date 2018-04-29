g++ -o testing_mic recognition.cpp -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`

./testing_mic -inmic yes -dict model/cmudict-en-us.dict -jsgf grammar/chess_grammar.jsgf -hmm model/cmusphinx-en-us-8khz-5.2
