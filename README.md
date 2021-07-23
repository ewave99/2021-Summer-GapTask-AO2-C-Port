# 2021 Summer Gap Task AO2 - C Port

This is an experiment I am doing with my original project in an effort to try 
to teach myself C.

Original: <https://github.com/ewave99/2021-Summer-GapTask-AO2>

## Differences from the original Python version:

- No validation for the input of the species name
- Names are case-sensitive when checking whether they already exist
- Text is right-aligned in table cells

## To do

- Create a branch to experiment with using a linked-list implementation of the list of Species records

## Bugs

- *2021-07-24*: if you delete a record, all the records that come after it become invisible since, when displaying the records, the program stops at the first blank record. We can fix this: (1) pick a record to be deleted. (2) For each record that comes after it, copy that record into the place to the left. (3) blank the trailing record at end since there will be duplicate records after copying the last one.
