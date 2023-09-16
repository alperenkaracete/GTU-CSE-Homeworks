CREATE TABLE agent (
	agentID INT AUTO_INCREMENT PRIMARY KEY,
    tourID INT,
    agencyID INT,
	agentName VARCHAR(255),
	agentTelephone VARCHAR(20),
	salary INT,
    available BOOLEAN,
    CONSTRAINT fkAgentTour FOREIGN KEY (tourID) REFERENCES tour (tourID),
    CONSTRAINT fkAgentAgency FOREIGN KEY (agencyID) REFERENCES travelagency (agencyID)
);