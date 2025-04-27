# LibraryDotProduct
C++ vs Python vs Python bindings. 
Tiny example of using Python bindings.

### 1. Install pybind:

$ sudo apt install pybind11-dev

### 2. Clone the repository
Clone the project to your local machine.

```bash
git clone https://your-repository-url.git
cd DotProduct
```

### 3. Create a build directory

```bash
mkdir build
cd build
```

### 4. Configure the project with CMake

```bash
cmake ..
```

### 5. Build the project

```bash
make
```

### 5. Check the C++ execution first:

```bash
cd bin
./dotProductTest
```

### 6. And then various version of Python execution:

```bash
cd ../../scripts
python3 test.py
```

and compare results/code.

