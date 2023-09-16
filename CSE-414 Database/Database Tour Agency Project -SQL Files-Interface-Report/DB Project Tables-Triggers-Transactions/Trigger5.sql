DELIMITER //

CREATE TRIGGER updateCapacityOfTourWhenDelete
AFTER DELETE ON booking
FOR EACH ROW
BEGIN
    IF OLD.tourID IS NOT NULL THEN
        UPDATE tour SET capacity = capacity + 1 WHERE tourID = OLD.tourID;
    END IF;
END//

DELIMITER ;