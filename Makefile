OBJ_DIR = obj
BIN_DIR = bin
TARGET = bin/a

INCLUDE = -I src/include

CPPFLAGS +=

CPP = g++
CPPSOURCES = $(shell find src/ -name "*.cc")
SOURCES = $(subst src/,,$(CPPSOURCES))
OBJECTS = $(addprefix $(OBJ_DIR)/,$(SOURCES:.cc=.o))
DEPFILES = $(OBJECTS:.o=.d)

.PHONY: all clean run


all: $(TARGET)

$(OBJ_DIR)/%.o: src/%.cc
	@echo "[cc] $< ..."
	@$(CPP) $(INCLUDE) -c $< $(CPPFLAGS) -o $@

$(OBJ_DIR)/%.d: src/%.cc
	@mkdir -pv $(dir $@)
	@echo "[dep] $< ..."
	@$(CPP) $(INCLUDE) $(CPPFLAGS) -MM -MT "$(OBJ_DIR)/$(<:.cc=.o)" "$<" > "$@"

sinclude $(DEPFILES)

$(TARGET) : $(OBJECTS)
	@echo "[link] $< ..."
	@mkdir -p $(BIN_DIR)
	@$(CPP) $(OBJECTS) -o $@ $(CPPFLAGS)
	@echo done

run:
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *~
