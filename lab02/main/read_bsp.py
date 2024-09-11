filtered_lines = []
with open("Untitled-1.txt", "r") as file:
    for line in file:
        if "DR_REG_GPIO_BASE" in line:
            filtered_lines.append(line)
with open("output-lines.txt", "w") as file:
    for line in filtered_lines:
        file.write(line)
