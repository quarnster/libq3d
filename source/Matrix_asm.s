
	.globl	_q3dMatrixTransformCopy,_q3dMatrixTransform

	.text

_q3dMatrixTransformCopy:
	sts.l	pr,@-r15
	mov	r5,r0
	mov	#4,r1
	mov	#8,r2
.cloop:
	fmov.s	@r4+,fr0
	fmov.s	fr0,@r0
	fmov.s	@r4+,fr0
	fmov.s	fr0,@(r0,r1)
	fmov.s	@r4+,fr0
	fmov.s	fr0,@(r0,r2)
	add	r7,r0
	dt	r6
	bf	.cloop

	lds.l	@r15+,pr
	nop
	rts
	nop


	! Multiply a set of 3D vectors with the matrix
	! (vectors are extended to 4D homogenous coordinates by
	!  setting W=1), and then normalize the resulting
	! vectors before storing them in the result array
	!
	! r4 = pointer to a source set of 3D vectors (n * 3 floats)
	! r5 = pointer to a destination set of 3D vectors (n * 4 floats)
	!      output vector is (x, y, z, -1/w)
	! r6 = number of vectors to transform
	! r7 = target pitch

_q3dMatrixTransform:
	mov	r5,r0
	mov	#4,r1
	mov	#8,r2
.loop:
	fmov.s	@r4+,fr0	! x
	fmov.s	@r4+,fr1	! y
	fmov.s	@r4+,fr2	! z
	fldi1	fr3		! w
	ftrv	xmtrx,fv0

	fdiv	fr3,fr0
	fmov.s	fr0,@r0
	fdiv	fr3,fr1
	fmov.s	fr1,@(r0,r1)
	fldi1	fr1
	fdiv	fr3,fr1
	fmov.s	fr1,@(r0,r2)
	add	r7,r0
	dt	r6
	bf	.loop

	rts
	nop

!	pref @r4
!	mov r5,r0
!	mov #4,r1
!	mov r4,r3
!	mov #8,r2
!	add #32,r3
!	mov #12,r7
!.loop:
!	fmov.s @r4+,fr0
!	fmov.s @r4+,fr1
!	fmov.s @r4+,fr2
!	fldi1 fr3
!	pref @r3
!	ftrv xmtrx,fv0
!	dt r6
!	fdiv fr3,fr0
!	fmov.s fr0,@r0
!	fdiv fr3,fr1
!	fmov.s fr1,@(r0,r1)
!	fdiv fr3,fr2
!	add #4*3,r3
!	fmov.s fr2,@(r0,r2)
!	fldi1 fr1
!	fneg fr1
!	fdiv fr3,fr1
!	fmov.s fr1,@(r0,r7)
!	bf/s .loop
!	add #4*4,r0
!	rts	
!	nop
