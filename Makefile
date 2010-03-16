all:
	@cd native/src && make && cd -

clean:
	@cd native/src && make clean && cd -

.PHONY: all clean

