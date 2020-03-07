
BINARY	= diablo

IDIR	= ./header

LIBDIR	= ./lib

SRC	= ./src

SRCS	= $(SRC)/diablo.cpp\
	  $(SRC)/Model.cpp\
	  $(SRC)/Frame.cpp

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
	rm -f out.ppm

re: fclean all

.PHONY:  clean fclean re
