CC       = gcc 
CFLAGS   = -Wall 
LDFLAGS  = -lpthread
OBJFILES = driver.o signal_generator.o data_processor.o
TARGET   = test 

all: $(TARGET) 

$(TARGET): $(OBJFILES) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 

clean:
	rm -f $(OBJFILES) $(TARGET) *~