5454def power(num,exponent): #num is base of expression and exponent is exponent of expressin -> num^exponent
    if exponent == 0: 
        return 1
    result = power(num, exponent//2)
    if exponent%2 == 0: return result*result
    else: return num*result*result
    

def sudokuSolver9x9(sudoku9x9):
  for i in range(9):
    for j in range(9):
      if sudoku9x9[i][j] == 0:
        for input in range(1,10):
          if isValid(sudoku9x9, i, j, input):
            sudoku9x9[i][j] = input
            sudokuSolver9x9(sudoku9x9)
            sudoku9x9[i][j] = 0
        return
 
  print(*sudoku9x9,sep="\n")

def isValid(sudoku9x9, row, col, input):
  # Check if the input is in the row
  if input in sudoku9x9[row]:
    return False

  # Check if the input is in the column
  for i in range(9):
    if sudoku9x9[i][col] == input:
      return False

  # Check if the input is in the 3x3 small part
  rowPart3x3 = (row // 3) * 3
  columnPart3x3 = (col // 3) * 3
  for i in range(3):
    for j in range(3):
      if sudoku9x9[rowPart3x3 + i][columnPart3x3 + j] == input:
        return False

  # If the input is not in any of the them, it is a valid placement input can be inserted.
  return True

# Example sudoku9x9
sudoku9x9 = [[2, 5, 0, 0, 3, 0, 9, 0, 1],
        [0, 1, 0, 0, 0, 4, 0, 0, 0],
        [4, 0, 7, 0, 0, 0, 2, 0, 8],
        [0, 0, 5, 2, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 9, 8, 1, 0, 0],
        [0, 4, 0, 0, 0, 3, 0, 0, 0],
        [0, 0, 0, 3, 6, 0, 0, 7, 2],
        [0, 7, 0, 0, 0, 0, 0, 0, 3],
        [9, 0, 3, 0, 0, 0, 6, 0, 4]]

def driverFunc():
    exponent=5
    num=2
    print ('Question 2')
    print (f'Exponent: {exponent}')
    print (f'Base: {num}')

    print(f'Result: {power(num,exponent)}')
    print('-------------------------------')
    print ('Question 3')
    print ('Before solving')
    print (*sudoku9x9,sep="\n")
    print ('After solving')
    sudokuSolver9x9(sudoku9x9)
    
driverFunc();    