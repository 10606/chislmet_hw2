compile_flags= -fsanitize=address -fsanitize=leak -fsanitize=undefined  -fdiagnostics-color=always -fdiagnostics-show-template-tree -fdiagnostics-generate-patch -fdiagnostics-format=text -lmgl2 -lncurses -lgtest -lpthread -lcurl -ljsoncpp -lmongoose -g -Wall -ftemplate-depth=10000 -std=c++17
source_files=methods/implicit_forward_flow.cpp methods/explicit_forward_flow.cpp methods/implicit_backward_flow.cpp methods/explicit_backward_flow.cpp methods/cheharda.cpp

main: main.cpp ${source_files}
	g++ ${compile_flags} -o main.cpp.elf main.cpp ${source_files}


name=example
resolution=720:720
frame_rate=5/1

fps=30
#pix_fmts=rgb48be
pix_fmts=yuv420p
encoder=libx264

video:
	ffmpeg -r ${frame_rate} -i ${name}-%d.jpg -codec:v ${encoder} -filter:v "fps=${fps}, format=${pix_fmts}, scale=${resolution}" ${name}.mp4
