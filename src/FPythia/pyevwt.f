
      subroutine pyevwt(wtxs)

      implicit none
      double precision vint(400), paru(200), parj(200)
      double precision wtxs, pt2
      integer mint(400), mstu(200), mstj(200)
      COMMON/PYINT1/MINT,VINT
      COMMON/PYDAT1/MSTU,PARU,MSTJ,PARJ

c      write(MSTU(11), *), 'called custom pyevwt'
      pt2 = vint(48)
      wtxs = pt2**3

      return
      end
