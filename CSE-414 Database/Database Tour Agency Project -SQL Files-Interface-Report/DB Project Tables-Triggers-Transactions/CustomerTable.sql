CREATE TABLE customer (
	custID INT AUTO_INCREMENT PRIMARY KEY,
	custName VARCHAR(50),
	custSurname VARCHAR(50),
	contactDetails VARCHAR(100),
	gender ENUM('Male', 'Female'),
	registrationDate DATE,
	custAddress VARCHAR(255)
);