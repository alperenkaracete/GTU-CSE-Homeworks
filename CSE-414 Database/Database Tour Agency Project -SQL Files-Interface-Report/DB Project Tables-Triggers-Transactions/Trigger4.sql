DELIMITER //

CREATE TRIGGER updateCapacityOfTourWhenRegister
AFTER INSERT ON booking
FOR EACH ROW
BEGIN
    IF NEW.tourID IS NOT NULL THEN
        UPDATE tour SET capacity = capacity - 1 WHERE tourID = NEW.tourID;
    END IF;
END//

DELIMITER ;