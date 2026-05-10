#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    // TODO: 在这里添加你的代码
    case ET_NONE:
      type_str = "Unknown";
      break;
    case ET_REL:
      type_str = "Relocatable";
      break;
    case ET_EXEC:
      type_str = "Executable";
      break;
    case ET_DYN:
      type_str = "Shared Object/PIE";
      break;
    default:
      type_str = "Unknown";
      break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码
  // 遍历两个文件
  for (int i = 0; i < 2; i++) {
    // 打开文件
    fd = open(filepath[i], O_RDONLY);
    if (fd == -1) {
      perror("open");
      continue;
    }
    
    // 读取 ELF header
    if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
      fprintf(stderr, "Failed to read ELF header from %s\n", filepath[i]);
      close(fd);
      continue;
    }
    
    // 验证是否为 ELF 文件（检查魔数）
    if (ehdr.e_ident[EI_MAG0] == ELFMAG0 &&
        ehdr.e_ident[EI_MAG1] == ELFMAG1 &&
        ehdr.e_ident[EI_MAG2] == ELFMAG2 &&
        ehdr.e_ident[EI_MAG3] == ELFMAG3) {
      // 打印文件路径和类型
      printf("File: %s\n", filepath[i]);
      print_elf_type(ehdr.e_type);
      printf("\n");
    } else {
      printf("File: %s\n", filepath[i]);
      printf("Not a valid ELF file\n\n");
    }
    
    close(fd);
  }
  
  return 0;
}
