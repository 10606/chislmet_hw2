release_flags = -lmgl2 -lpthread\
		-O3 -mtune=native -march=native -g -Wall -ftemplate-depth=10000 -std=c++17

compile_flags = -fsanitize=address -fsanitize=leak -fsanitize=undefined \
		-fdiagnostics-color=always -fdiagnostics-show-template-tree -fdiagnostics-generate-patch -fdiagnostics-format=text\
		-lmgl2 -lpthread\
		-g -Wall -ftemplate-depth=10000 -std=c++17

method_object_files = methods/implicit_forward_flow.o\
		      methods/explicit_forward_flow.o\
		      methods/implicit_backward_flow.o\
		      methods/explicit_backward_flow.o\
		      methods/cheharda.o\
		      methods/method_utils.o\
		      methods/common_implicit.o

plots_object_files = plots/calc_min_max_and_draw_plots.o\
		     plots/plots.o\
		     plots/start_parameters.o\
		     plots/visualization.o

pictures: plots_main
	rm pictures/*
	plots/plots_main.cpp.elf

plots_main: plots/plots_main.cpp ${plots_object_files} ${method_object_files}
	g++ ${release_flags} -o plots/plots_main.cpp.elf plots/plots_main.cpp ${method_object_files} ${plots_object_files}

main: main.cpp ${method_object_files} ${method_object_files}
	g++ ${compile_flags} -o main.cpp.elf main.cpp ${method_object_files} ${plots_object_files}

%.o: %.cpp
	g++ ${release_flags} -c -o $@ $^

picture_name = pictures/example
video_name = pictures/video
resolution = 1280:720
frame_rate = 30/1

fps = 30
#pix_fmts = rgb48be
pix_fmts = rgba
encoder = libx264

video:
	ffmpeg -r ${frame_rate} -i ${picture_name}-%d.png -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${video_name}.mp4
