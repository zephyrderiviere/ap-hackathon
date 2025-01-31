# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = 

# Bibliothèques SFML
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Répertoire des fichiers sources
SRC_DIR = .

# Répertoire des fichiers objets
OBJ_DIR = obj

# Liste des fichiers sources (ajoutez tous vos fichiers .cpp ici)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Liste des fichiers objets (générés à partir des fichiers sources)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Nom de l'exécutable final
TARGET = game

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(SFML_LIBS)

# Règle pour compiler chaque fichier source en fichier objet
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Règle pour recompiler tout le projet
rebuild: clean all

# Indique que les règles 'all', 'clean', et 'rebuild' ne sont pas des fichiers
.PHONY: all clean rebuild
