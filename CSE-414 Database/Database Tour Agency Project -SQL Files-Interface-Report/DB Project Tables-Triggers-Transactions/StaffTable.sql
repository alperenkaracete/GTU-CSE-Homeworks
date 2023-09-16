CREATE TABLE staff (
	staffID INT AUTO_INCREMENT PRIMARY KEY,
    agencyID INT,
    agencyTelephone VARCHAR(20),
    adress VARCHAR(100),
	jobCode VARCHAR(255),
	title VARCHAR(255),
    salary INT,
    CONSTRAINT fkStaffAgency FOREIGN KEY (agencyID) REFERENCES travelagency (agencyID)
);