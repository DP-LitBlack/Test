CC       = gcc 
CFLAGS   = -Wall 
LDFLAGS  = -lpthread
OBJFILES = driver.o signal_generator.o data_processor.o udp_server.o data_logging.o
TARGET   = test 

all: $(TARGET) 

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 

tests: all
	sleep 1
	./$(TARGET)
	python3 -m unittest -v test_data_processor.py

clean:
	rm -f $(OBJFILES) $(TARGET) *~