# Inventory Management System

A console-based inventory management system written in C++.

It handles adding, updating, searching, and deleting inventory items. Records are stored in a binary file (`shop.dat`), and there are two menus: an employee menu (password protected, password is `abc`) for managing stock, and a customer menu for purchases.

## Running

```bash
g++ main.cpp -o inventory
./inventory
```

The program originally used `conio.h` and `system("cls")`, so it only built on Windows. It now builds on Linux and macOS too (the Windows behaviour is unchanged).

## What it does

- Employee menu (password `abc`): add new products, display stock, refill stock, remove an item.
- Customer menu: purchase an item (it prints the total price and updates the stock) or display the stock.
- Everything is saved to `shop.dat` in the working directory, so the stock persists between runs.

## Sample run

Real output from a run on Linux: add one product as the employee, then buy 2 of them as the customer.

```
Enter the No. of Products that you wish to add:

Input the name, price and the quantity of item respectively

Enter the Name , the price and then the quantity

item updated

Stock Updated!!
```

```
PARTICULARS     STOCK AVAILABLE                  PRICE

Widget                  10                      9.99
```

```
Enter the product's name

Enter quantity:

Stock updated.

Total price to be paid:19.98
```
