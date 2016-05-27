      subroutine openlhef(filename)
      character *(*) filename
      OPEN(UNIT=88, FILE=filename)
      return
      end
