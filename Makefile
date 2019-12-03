.DEFAULT: pictures
.PHONY: pictures video



OS=$(shell lsb_release -si)

ifeq ($(OS),Ubuntu)
	mgl_flag = -lmgl
else
	mgl_flag = -lmgl2
endif

release_flags = -lpthread\
		-O3 -mtune=native -march=native -g -Wall -ftemplate-depth=10000 -std=c++17

compile_flags = -fsanitize=address -fsanitize=leak -fsanitize=undefined \
		-fdiagnostics-color=always -fdiagnostics-generate-patch \
		-lpthread\
		-g -Wall -ftemplate-depth=10000 -std=c++17

header_method_files = 	methods/cheharda.h\
			methods/common_implicit.h\
			methods/explicit_backward_flow.h\
			methods/explicit_forward_flow.h\
			methods/implicit_backward_flow.h\
			methods/implicit_forward_flow.h\
			methods/fake_method_copy.h\
			methods/method_utils.h\
			methods/predictor_corrector.h\

header_plots_files =	plots/calc_min_max_and_draw_plots.h\
			plots/plots.h\
			plots/plots_utils.h\
			plots/visualization.h\
			utils.h


method_object_files = methods/implicit_forward_flow.o\
		      methods/explicit_forward_flow.o\
		      methods/implicit_backward_flow.o\
		      methods/explicit_backward_flow.o\
		      methods/cheharda.o\
		      methods/method_utils.o\
		      methods/fake_method_copy.o\
		      methods/common_implicit.o\
					methods/predictor_corrector.o\

plots_object_files = plots/calc_min_max_and_draw_plots.o\
		     plots/plots.o\
		     plots/visualization.o

pc_main: methods/pc_main.cpp.elf
		./pc_main.cpp.elf

run_main: main.cpp.elf
		rm -rf pictures/*
		./main.cpp.elf

clean:
	rm -rf plots/*.o
	rm -rf methods/*.o
	rm -rf plots/*.elf
	rm -rf methods/*.elf
	rm -rf ./*.o
	rm -rf ./*.elf

pictures: plots/plots_main.cpp.elf
	-mkdir pictures
	-rm pictures/*
	plots/plots_main.cpp.elf

plots/plots_main.cpp.elf: plots/plots_main.o ${plots_object_files} ${method_object_files}
	g++ ${release_flags} -o plots/plots_main.cpp.elf plots/plots_main.o ${method_object_files} ${plots_object_files} ${mgl_flag}

main.cpp.elf: main.cpp ${plots_object_files} ${method_object_files}
	g++ ${release_flags} -o main.cpp.elf main.cpp ${method_object_files} ${plots_object_files} ${mgl_flag}

methods/pc_main.cpp.elf: methods/pc_main.cpp ${plots_object_files} ${method_object_files}
	g++ ${release_flags} -o pc_main.cpp.elf methods/pc_main.cpp ${method_object_files} ${plots_object_files} ${mgl_flag}

methods/%.o: methods/%.cpp ${header_method_files}
	g++ ${release_flags} -c -o $@ $< ${mgl_flag}

plots/%.o: plots/%.cpp ${header_plots_files}
	g++ ${release_flags} -c -o $@ $< ${mgl_flag}

picture_name = pictures/
video_name = pictures/video
resolution = 1280:720
frame_rate = 30/1

fps = 30
#pix_fmts = rgb48be
pix_fmts = rgba
encoder = libx264

video_T_z:
	ffmpeg -r ${frame_rate} -i ${picture_name}T_z_%d.png -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${video_name}_T_z.mp4

video_T_t:
	ffmpeg -r ${frame_rate} -i ${picture_name}T_t_%d.png -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${video_name}_T_t.mp4

video_X_z:
	ffmpeg -r ${frame_rate} -i ${picture_name}X_z_%d.png -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${video_name}_X_z.mp4

video_X_t:
	ffmpeg -r ${frame_rate} -i ${picture_name}X_t_%d.png -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${video_name}_X_t.mp4


video: video_T_z video_T_t video_X_t video_X_z
