# Steven Mare - MRXSTE008
# 11 May 2018
# for CSC3022H Assignment 5

outfile = "out*.raw";
file1 = "sample_input/countdown40sec_44100_signed_16bit_mono.raw"
file2 = "sample_input/siren40sec_44100_signed_16bit_mono.raw"
file3 = "sample_input/beez18sec_44100_signed_16bit_mono.raw"
file4 = "sample_input/frogs18sec_44100_signed_16bit_mono.raw"
file5 = "sample_input/countdown40sec_44100_signed_16bit_stereo.raw"
file6 = "sample_input/siren40sec_44100_signed_16bit_stereo.raw"
file7 = "sample_input/beez18sec_44100_signed_16bit_stereo.raw"
file8 = "sample_input/frogs18sec_44100_signed_16bit_stereo.raw"

default: help	

driver_o: driver.cpp
	g++ -c -o driver.o driver.cpp -std=c++11

executable: driver.o
	g++ -o samp driver.o -std=c++11

functions: clean driver_o executable

mono_add: functions
	./samp -r 44100 -b 16 -c 1 \
	-add $(file1) $(file2)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_cut: functions
	./samp -r 44100 -b 16 -c 1 \
	-cut 124000 364000 $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_radd: functions
	./samp -r 44100 -b 16 -c 1 \
	-radd 124000 364000 4000 244000 $(file1) $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_cat: functions
	./samp -r 44100 -b 16 -c 1 \
	-cat $(file3) $(file4)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_v: functions
	./samp -r 44100 -b 16 -c 1 \
	-v 0.2 0.1 $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_rev: functions
	./samp -r 44100 -b 16 -c 1 \
	-rev $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_rms: functions
	./samp -r 44100 -b 16 -c 1 \
	-rms $(file1)	

mono_norm: functions
	./samp -r 44100 -b 16 -c 1 \
	-norm 1000 1000 $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_fadein: functions
	./samp -r 44100 -b 16 -c 1 \
	-fadein 11 $(file1)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)	

mono_fadeout: functions
	./samp -r 44100 -b 16 -c 1 \
	-fadeout 17 $(file3)
	play -r 44100 -e signed -b 16 -c 1 $(outfile)

stereo_add: functions
	./samp -r 44100 -b 16 -c 2 \
	-add $(file5) $(file6)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_cut: functions
	./samp -r 44100 -b 16 -c 2 \
	-cut 124000 424000 $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_radd: functions
	./samp -r 44100 -b 16 -c 2 \
	-radd 124000 484000 4000 364000 $(file5) $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_cat: functions
	./samp -r 44100 -b 16 -c 2 \
	-cat $(file7) $(file8)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_v: functions
	./samp -r 44100 -b 16 -c 2 \
	-v 0.1 0.4 $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_rev: functions
	./samp -r 44100 -b 16 -c 2 \
	-rev $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_rms: functions
	./samp -r 44100 -b 16 -c 2 \
	-rms $(file5)	

stereo_norm: functions
	./samp -r 44100 -b 16 -c 2 \
	-norm 3555 1000 $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_fadein: functions
	./samp -r 44100 -b 16 -c 2 \
	-fadein 15 $(file5)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

stereo_fadeout: functions
	./samp -r 44100 -b 16 -c 2 \
	-fadeout 17 $(file7)
	play -r 44100 -e signed -b 16 -c 2 $(outfile)	

tests: clean unitTests.cpp
	g++ -c -o unitTests.o unitTests.cpp --std=c++11 -w
	g++ -o unitTests unitTests.o --std=c++11 -w
	./unitTests

clean:
	rm -f *.o
	rm -f *.raw
	rm -f samp
	rm -f unitTests

help:
	less README
