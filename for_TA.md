### `for_TA.md`

#### **Lab Overview**
This lab, named *Bomb++*, is a customized version of CMU’s *bomblab*. The redesign focuses on introducing features to prevent plagiarism, adding interactivity, and ensuring a personalized learning experience. Below, we outline the main features, necessary handout contents, runtime environment requirements, and some ideas for further improvement.

---

#### **Key Features**
1. **`config.txt` Integration**:
    - **Customizable Student ID**: The lab generates unique answers for each student based on a hash of their ID specified in `config.txt`. This ensures that answers are unique for each student and the process of retrieving the correct answers remains equally challenging regardless of the hash value.
    - **Level Skipping**: Students can modify parameters in `config.txt` to skip levels where they encounter significant difficulty. This feature prevents frustration while preserving the overall learning experience.
    - **Story Mode**: A new storyline has been added to make the lab more engaging. Students can toggle the storyline mode on or off via the `config.txt` file.

2. **Unified Executable**:
    - All necessary configuration is handled through `config.txt`, allowing the executable file to remain consistent across students. This eliminates discrepancies and simplifies distribution.

3. **File-Based Input**:
    - The lab reads input from `config.txt`, streamlining the configuration process and reducing potential setup issues.

---

#### **Runtime Environment**
The lab is designed to run in the following environment:

1. **Operating System**:
    - Default environment: **x86-based Ubuntu 22.04** (64-bit).
    - The lab is built and tested on this version of Ubuntu to ensure compatibility and consistent behavior.

2. **Compiler**:
    - **GCC**: Version 11.4.0 or newer.

3. **Debugger**:
    - **GDB**: The GNU Debugger should be available and compatible with the environment for debugging and learning purposes.

4. **Libraries**:
    - Standard C/C++ libraries should be pre-installed. The lab does not require any third-party dependencies.

---

#### **Handout Contents**
The following files should be included in the lab handout:

1. **`bomb++`**:
    - The compiled executable for the lab. This is the primary program students will interact with.

2. **`fail.txt`**:
    - A file that provides entertaining outputs after a "bomb explosion." While it has no functional significance, it adds an element of humor and enjoyment to the lab.

3. **`config.txt`**:
    - The configuration file where students input their ID, enable/disable features (e.g., Story Mode), and modify parameters for skipping levels. Detailed documentation on the fields should be provided in the handout.

4. **`main.cpp`**:
    - The source code of the lab, allowing students to study its implementation and practice debugging. It also ensures transparency in how the lab operates.

5. **Tutor Materials**:
    - **`gdb-tutor`**: An executable designed to help students learn and practice using GDB, focusing on debugging techniques necessary for the lab.
    - **`gdb-tutor.c`**: The source code corresponding to the `gdb-tutor` executable. It allows students to understand how the tutorial works and serves as a hands-on learning tool.

---

#### **Additional TA-Only Files**
The following files are for TAs only and **should not be included in the handout**:

1. **`answer`**:
    - An executable designed to generate the answers corresponding to a given student ID. This ensures consistent and accurate answer generation for testing or verifying student work.

---

#### **Further Improvement Suggestions**
1. **Code Obfuscation and Assembly Code**:
    - Apply code obfuscation or packing techniques (e.g., using tools such as `UPX` or custom shellcode) to make reverse engineering the binary more challenging. This prevents students from using decompilers to bypass the intended learning objectives.
    - Provide the extracted assembly code (e.g., using `objdump`) alongside the packed binary to ensure students can analyze and debug if needed:
      ```asm
      00401560 <phase_1>:
      401560:    55                      push   %rbp
      401561:    48 89 e5                mov    %rsp,%rbp
      401564:    48 83 ec 10             sub    $0x10,%rsp
      401568:    89 7d fc                mov    %edi,-0x4(%rbp)
      40156b:    48 89 75 f0             mov    %rsi,-0x10(%rbp)
      ...
      ```

2. **Dynamic Analysis Resistance**:
    - Introduce anti-debugging techniques in critical phases (e.g., phases 1 to the final phase) to detect and resist dynamic analysis tools like GDB.
    - Allow dynamic debugging during the initial phase (`phase_0`), where the hash for the student ID is generated. This gives students an opportunity to familiarize themselves with debugging tools. 
    - **Optional Honor Part**: Provide a variant where dynamic debugging is disallowed throughout all phases for advanced students, significantly increasing difficulty.

3. **Enhanced Configuration**:
    - Expand the `config.txt` options to include features like:
      - Adjusting difficulty levels.
      - Customizing story mode themes.
      - Logging successful attempts.
      - etc.

4. **Interactive Story Enhancements**:
    - Make the story mode more interactive by branching based on student performance or choices. This can make the lab more engaging and provide a gamified learning experience.
