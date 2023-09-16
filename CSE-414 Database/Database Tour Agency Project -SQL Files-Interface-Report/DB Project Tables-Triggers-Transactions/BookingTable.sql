CREATE TABLE booking (
	bookingID INT AUTO_INCREMENT PRIMARY KEY,
	custID INT NOT NULL,
	busID INT,
	hotelID INT,
	bookingDate DATE,
    totalDay INT,
    roomID INT,
    price INT,
    startDate DATE,
    endDate DATE,
	cityName VARCHAR(100),
    CONSTRAINT fkBookingCustomer FOREIGN KEY (custID) REFERENCES customer (custID),
    CONSTRAINT fkBookingHotel FOREIGN KEY (hotelID) REFERENCES hotel (hotelID),
    CONSTRAINT fkBookingBus FOREIGN KEY (busID) REFERENCES bus (busID),
    CONSTRAINT fkBookingTour FOREIGN KEY (tourID) REFERENCES tour(tourID)
);