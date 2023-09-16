DELIMITER //

CREATE PROCEDURE updateTourDuration(
    IN tempTourID INT,
		newDuration INT
)
BEGIN
    UPDATE tour SET duration = newDuration WHERE tourID = tempTourID;
END//

DELIMITER ;