
#define	_GETSINGLE(p)	p::GetInst()

#define	_SINGLETON(p)		\
	public:					\
	static p* GetInst()		\
	{						\
		static	p	Inst;	\
		return	&Inst;		\
	}						\
	protected:				\
	p(void);				\
	public:					\
	~p(void);


#define	_SYNTHESIZE_REF_INHER( varType, varName, FunName )	\
	protected:				\
	varType	varName;		\
	public:					\
	void	Set##FunName( const varType& var )	{ varName = var;	}	\
	const varType&	Get##FunName()	{	return	varName;	}


#define	_SYNTHESIZE_INHER( varType, varName, FunName )	\
	protected:				\
	varType	varName;		\
	public:					\
	void	Set##FunName( varType var )	{ varName = var;	}	\
	varType	Get##FunName()	{	return	varName;	}

#define	EASY_CAST( Type, Target )	((Type)Target)