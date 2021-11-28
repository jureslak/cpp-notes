# cpp-notes
Zapiski o C++-u. Objavljena verzija je na
[https://e6.ijs.si/~jslak/c++/](https://e6.ijs.si/~jslak/c++/)

# Generating the notes

The setup assumes you are working in a Linux environment. The instrcutions need only slight
modifications for Windows. Make sure you have a recent enough version of Python 3 installed.

Run
```
python -m venv venv3
source venv3/bin/activate
pip install -r requirements.txt
```
to prepare the development environment.

Change to the `notes` directory:
```
cd notes
```

Every time you wish to compile the notes, run
```
make html
```
(or `make latex`, or other).

Edit the sources in the `source/` folder to update the notes.
The generated notes can be viewed in a browser by opening the `build/html/index.html`
file.

---
Jure Slak

