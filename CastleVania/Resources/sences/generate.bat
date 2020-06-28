for %%f in (scene*.init) do (
    echo %%~nf
   type %%~nf.res %%~nf.init > %%~nf.txt
)
