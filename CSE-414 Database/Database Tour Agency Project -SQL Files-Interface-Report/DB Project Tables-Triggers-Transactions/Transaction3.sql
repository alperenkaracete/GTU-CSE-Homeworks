DELIMITER //

CREATE PROCEDURE updateTourRoute(
    IN tempTourID INT,
		newRoute VARCHAR(255)
)
BEGIN
    UPDATE tour SET route = newRoute WHERE tourID = tempTourID;
END//

DELIMITER ;