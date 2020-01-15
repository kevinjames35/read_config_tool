#simple make file
all:
	gcc read_config_tool.c -o read_config_tool -lpthread
clean:
	rm -f read_config_tool
