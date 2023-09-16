CREATE TABLE bus (
	busID INT AUTO_INCREMENT PRIMARY KEY,
    driverID INT,
    tourID INT,
	busName VARCHAR(100),
	seatingCapacity INT,
	availability BOOLEAN,
    destination VARCHAR(100),
    CONSTRAINT fkBusDriver FOREIGN KEY (driverID) REFERENCES driver (driverID),
    CONSTRAINT fkBusTour FOREIGN KEY (tourID) REFERENCES tour (tourID)
);