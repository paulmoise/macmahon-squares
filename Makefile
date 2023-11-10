CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -Wall -g3

# Dossiers contenant les fichiers source (.cpp)
SRC_DIR = src

# Dossiers contenant les fichiers en-tête (.hpp)
INC_DIR = header

# Dossier de sortie pour les fichiers objets (.o)
OBJ_DIR = obj

# Dossier de sortie pour les fichiers exécutables
BIN_DIR = bin

# Nom de l'exécutable final
TARGET = main

# Utilisation de find pour obtenir la liste de tous les fichiers source
SOURCES = $(shell find $(SRC_DIR) -type f -name "*.cpp")

# Générer la liste des fichiers objets correspondants
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Commande de compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Règle de construction de l'exécutable
$(BIN_DIR)/$(TARGET): $(OBJECTS) | $(BIN_DIR)
    $(CXX) $(CXXFLAGS) -I$(INC_DIR) $^ -o $@

# Commande pour nettoyer les fichiers objets et l'exécutable
clean:
    rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET)

# Commande pour compiler le projet
all: $(BIN_DIR)/$(TARGET)

# Création du dossier de sortie pour les fichiers objets
$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

# Création du dossier de sortie pour les exécutables
$(BIN_DIR):
    mkdir -p $(BIN_DIR)

.PHONY: clean all

# Exécution par défaut : compile le projet
default: all
