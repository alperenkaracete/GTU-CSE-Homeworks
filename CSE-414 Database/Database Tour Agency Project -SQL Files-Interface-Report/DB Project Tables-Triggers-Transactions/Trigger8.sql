DELIMITER //

CREATE TRIGGER IncreaseSeatingCapacity
AFTER DELETE ON booking
FOR EACH ROW
BEGIN
    UPDATE bus SET seatingCapacity = seatingCapacity + 1 WHERE busID = OLD.busID;
END//

DELIMITER ;
