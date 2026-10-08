CC=gcc
CFLAGS=-Wall -Wextra -O2 -Iinclude
SRC_DIR=src
RES_DIR=results
SRCS=$(wildcard $(SRC_DIR)/*.c)
TARGET=benchmark
GNUPLOT=gnuplot
PLOT_SCRIPT=plot.gp

.PHONY: all demo full test clean run dirs random sorted reverse nearly duplicates plot graph

define draw_plot
	@echo "--> Graph: $(RES_DIR)/plot_$(1).png"
	@$(GNUPLOT) -e "type='$(1)'" $(PLOT_SCRIPT)
endef

all: dirs $(TARGET)

dirs:
	@mkdir -p $(RES_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build successful! Executable ready at ./$(TARGET)"

demo: all
	@./$(TARGET) --demo random

test: all
	@./$(TARGET) --test

random: all
	@./$(TARGET) --full random
	$(call draw_plot,random)

sorted: all
	@./$(TARGET) --full sorted
	$(call draw_plot,sorted)

reverse: all
	@./$(TARGET) --full reverse
	$(call draw_plot,reverse_sorted)

nearly: all
	@./$(TARGET) --full nearly
	$(call draw_plot,nearly_sorted)

duplicates: all
	@./$(TARGET) --full duplicates
	$(call draw_plot,many_duplicates)

full: all
	@./$(TARGET) --full all
	@for t in random sorted reverse_sorted nearly_sorted many_duplicates; do \
		echo "--> Graph: $(RES_DIR)/plot_$$t.png"; \
		$(GNUPLOT) -e "type='$$t'" $(PLOT_SCRIPT); \
	done

plot:
	@for t in random sorted reverse_sorted nearly_sorted many_duplicates; do \
		echo "--> Graph: $(RES_DIR)/plot_$$t.png"; \
		$(GNUPLOT) -e "type='$$t'" $(PLOT_SCRIPT); \
	done

graph: plot

run: demo

clean:
	rm -f $(TARGET) $(RES_DIR)/plot_*.png
	@echo "Clean completed."

