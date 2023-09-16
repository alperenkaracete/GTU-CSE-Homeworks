DELIMITER //

CREATE PROCEDURE deleteBooking(
    IN tempBookingID INT
)
BEGIN
    DECLARE bookingCount INT;
    
    START TRANSACTION;
    
    SELECT COUNT(*) INTO bookingCount FROM booking WHERE bookingID = tempBookingID;
    
    IF bookingCount > 0 THEN
        DELETE FROM booking WHERE bookingID = tempBookingID;
        COMMIT;
    ELSE
        ROLLBACK;
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Error deleting booking!';
    END IF;
    
END//

DELIMITER ;