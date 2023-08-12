# Chemical-element-emission-table
Navigate in the interactive table with the arrow keys ('W', 'A', 'S' or 'D') and obtain the electronic distribution of a given atom whit its respective emission and absorption spectra.  
![ezgif com-video-to-gif (1)](https://github.com/exponeciale/chemical-element-emission-table/assets/132215795/712d578f-b411-49d0-9680-7c44090c9137)  

The spectra were obtained using the Rydberg formula extended to any hydrogen-like atom, i.e. considering only one electron in the outermost orbital of the given atom.  
Rₘ = R∞/1+mₑ/M  
Rₘ is the Rydberg adjusted constant for a given atom with one electron and intrinsic mass 'M'.  
mₑ is the mass of the electron.  
R∞ = 1.096776E⁷ m⁻¹  
M is the mass of its atomic nucleus  

(1/λₐ) = RZ²((1/₁n²)-(1/₂n²))  
λₐ is the wavelength of light emitted in vacuum.  
R is the adjusted Rydberg constant for a given element.  
Z is the atomic number;  
₁n and ₂n are integers such that ₁n < ₂n.  

install the xfce4-terminal graphical environment and the curses module  
sudo apt install xfce4-terminal libncursesw5-dev -y  
compile: gcc spectrumTable.c -o spectrumTable -lm -lncursesw
