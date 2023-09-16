CREATE TABLE travelagency (
	agencyID INT AUTO_INCREMENT PRIMARY KEY,
	agencyName VARCHAR(100) NOT NULL,
	cityID INT,
	phone VARCHAR(20),
	address VARCHAR(255),
    city VARCHAR(100),
    mail VARCHAR(100),
    CONSTRAINT fkTravelAgencyCity FOREIGN KEY (cityID) REFERENCES city (cityID)
);