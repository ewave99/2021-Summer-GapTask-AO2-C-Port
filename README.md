# 2021 Summer Gap Task AO2 - C Port

This is an experiment I am doing with my original project in an effort to try 
to teach myself C.

Original: <https://github.com/ewave99/2021-Summer-GapTask-AO2>

## Differences from the original Python version:

- No validation for the input of the species name
- Names are case-sensitive when checking whether they already exist
- Text is right-aligned in table cells
- Bar chart is displayed in the terminal rather than an external graphical
  library. However, the scale of the bar chart is responsive to the width of the
  terminal.
- The Python version is programmed in an object-oriented fashion, which is
  not possible in C. So the C is programmed in a procedural fashion.

## To do

- Create a branch to experiment with using a linked-list implementation of the list of Species records

## Bugs

*None at present*

## Build

- `make`

## Run

- `./main`
