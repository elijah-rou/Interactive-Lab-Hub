arecord -D plughw:1,0 -f cd -c1 -r 48000 -d 5 -t wav nooooo.wav
python3 i_have_the_highground.py nooooo.wav
