# Nome do programa de saída
TARGET = simulacao_algoritmos_escalonamento

# Compilador a ser usado
CXX = g++

# Opções de compilação
CXXFLAGS = -Wall -Wextra -std=c++11 -DINPUT_FILE=\"$(INPUTSDIR)/$(INPUT_FILE)\"

# Diretório de origem (onde estão os arquivos-fonte e de cabeçalho)
SRCDIR = src

# Diretório de entrada (onde está o arquivo entrada.txt)
INPUTSDIR = input

# Nome do arquivo de entrada
INPUT_FILE = entrada.txt

# Lista de arquivos-fonte (relativos ao diretório de origem)
SOURCES = $(wildcard $(SRCDIR)/*.cc)

# Lista de arquivos de objeto gerados a partir dos arquivos-fonte
OBJECTS = $(SOURCES:.cc=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o programa
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para limpar arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET)
