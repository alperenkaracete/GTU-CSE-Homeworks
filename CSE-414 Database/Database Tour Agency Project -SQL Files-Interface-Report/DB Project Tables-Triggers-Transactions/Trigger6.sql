DELIMITER //

CREATE TRIGGER updateBookingTotalDay
AFTER UPDATE ON tour
FOR EACH ROW
BEGIN

    IF OLD.duration <> NEW.duration THEN

        UPDATE booking
        SET totalDay = NEW.duration
        WHERE tourID = NEW.tourID;
    END IF;
END//

DELIMITER ;