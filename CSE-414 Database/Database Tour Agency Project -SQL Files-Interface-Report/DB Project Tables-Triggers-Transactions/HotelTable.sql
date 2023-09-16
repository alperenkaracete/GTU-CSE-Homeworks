CREATE TABLE hotel (
	hotelID INT AUTO_INCREMENT PRIMARY KEY,
	hotelName VARCHAR(255),
	cityID INT,
    hotelPrice INT,
    hotelTelephoneNo VARCHAR(20),
    roomCount INT,
	CONSTRAINT fkHotelCity FOREIGN KEY (cityID) REFERENCES city (cityID)
);

