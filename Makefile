
BINARY	= render

IDIR	= ./header

LIBDIR	= ./lib

SRC	= ./src

SRCS	= $(SRC)/main.cpp\
	  $(SRC)/Model.cpp\
	  $(SRC)/Frame.cpp\
	  $(SRC)/tgaimage.cpp

OBJS	= $(SRCS:.cpp=.o)

HEADERS	= $(IDIR)/*

LIBS	=

CC	= g++

CFLAGS	= -I$(IDIR) -L$(LIBDIR)

%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: 	$(OBJS)
	$(CC) -o $(BINARY) $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(SRC)/*.o

fclean: clean
	rm -f $(BINARY)

re: fclean all

.PHONY:  clean fclean re
