release_flags = -lmgl2 -lpthread\
		-O3 -mtune=native -march=native -g -Wall -ftemplate-depth=10000 -std=c++17

compile_flags = -fsanitize=address -fsanitize=leak -fsanitize=undefined \
		-fdiagnostics-color=always -fdiagnostics-show-template-tree -fdiagnostics-generate-patch -fdiagnostics-format=text\
		-lmgl2 -lpthread\
		-g -Wall -ftemplate-depth=10000 -std=c++17

method_source_files = methods/implicit_forward_flow.cpp\
		      methods/explicit_forward_flow.cpp\
		      methods/implicit_backward_flow.cpp\
		      methods/explicit_backward_flow.cpp\
		      methods/cheharda.cpp\
		      methods/method_utils.cpp

plots_source_files = plots/calc_min_max_and_draw_plots.cpp\
		     plots/plots.cpp\
		     plots/start_parameters.cpp\
		     plots/visualization.cpp

pictures: plots_main
	rm pictures/*
	plots/plots_main.cpp.elf

plots_main: plots/plots_main.cpp ${method_source_files} ${method_source_files}
	g++ ${release_flags} -o plots/plots_main.cpp.elf plots/plots_main.cpp ${method_source_files} ${plots_source_files}

main: main.cpp ${method_source_files} ${method_source_files}
	g++ ${compile_flags} -o main.cpp.elf main.cpp ${method_source_files} ${plots_source_files}

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
