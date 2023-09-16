CREATE TABLE tour (
	tourID INT AUTO_INCREMENT PRIMARY KEY,
    hotelID INT,
	tourName VARCHAR(100),
	location VARCHAR(100),
	route VARCHAR(255),
	time DATE,
    duration INT,
	capacity INT,
    CONSTRAINT fktourhotel FOREIGN KEY (hotelID) REFERENCES hotel (hotelID)
);