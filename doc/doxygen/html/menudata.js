/*
@ @licstart  The following is the entire license notice for the
JavaScript code in this file.

Copyright (C) 1997-2017 by Dimitri van Heesch

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

@licend  The above is the entire license notice
for the JavaScript code in this file
*/
var menudata = {
    children: [
        {text: "Pagina Principale", url: "index.html"},
        {
            text: "Namespace", url: "namespaces.html", children: [
                {text: "Lista dei namespace", url: "namespaces.html"},
                {
                    text: "Membri dei namespace", url: "namespacemembers.html", children: [
                        {text: "Tutto", url: "namespacemembers.html"},
                        {text: "Funzioni", url: "namespacemembers_func.html"},
                        {text: "Tipi enumerati (enum)", url: "namespacemembers_enum.html"},
                        {text: "Valori del tipo enumerato", url: "namespacemembers_eval.html"}]
                }]
        },
        {
            text: "Classi", url: "annotated.html", children: [
                {text: "Elenco dei tipi composti", url: "annotated.html"},
                {text: "Indice dei tipi composti", url: "classes.html"},
                {text: "Gerarchia delle classi", url: "inherits.html"},
                {
                    text: "Membri dei composti", url: "functions.html", children: [
                        {
                            text: "Tutto", url: "functions.html", children: [
                                {text: "a", url: "functions.html#index_a"},
                                {text: "b", url: "functions_b.html#index_b"},
                                {text: "c", url: "functions_c.html#index_c"},
                                {text: "d", url: "functions_d.html#index_d"},
                                {text: "e", url: "functions_e.html#index_e"},
                                {text: "f", url: "functions_f.html#index_f"},
                                {text: "g", url: "functions_g.html#index_g"},
                                {text: "i", url: "functions_i.html#index_i"},
                                {text: "k", url: "functions_k.html#index_k"},
                                {text: "l", url: "functions_l.html#index_l"},
                                {text: "m", url: "functions_m.html#index_m"},
                                {text: "n", url: "functions_n.html#index_n"},
                                {text: "o", url: "functions_o.html#index_o"},
                                {text: "p", url: "functions_p.html#index_p"},
                                {text: "r", url: "functions_r.html#index_r"},
                                {text: "s", url: "functions_s.html#index_s"},
                                {text: "t", url: "functions_t.html#index_t"},
                                {text: "u", url: "functions_u.html#index_u"},
                                {text: "y", url: "functions_y.html#index_y"},
                                {text: "~", url: "functions_0x7e.html#index_0x7e"}]
                        },
                        {
                            text: "Funzioni", url: "functions_func.html", children: [
                                {text: "a", url: "functions_func.html#index_a"},
                                {text: "c", url: "functions_func_c.html#index_c"},
                                {text: "d", url: "functions_func_d.html#index_d"},
                                {text: "e", url: "functions_func_e.html#index_e"},
                                {text: "g", url: "functions_func_g.html#index_g"},
                                {text: "i", url: "functions_func_i.html#index_i"},
                                {text: "k", url: "functions_func_k.html#index_k"},
                                {text: "l", url: "functions_func_l.html#index_l"},
                                {text: "m", url: "functions_func_m.html#index_m"},
                                {text: "n", url: "functions_func_n.html#index_n"},
                                {text: "o", url: "functions_func_o.html#index_o"},
                                {text: "p", url: "functions_func_p.html#index_p"},
                                {text: "r", url: "functions_func_r.html#index_r"},
                                {text: "s", url: "functions_func_s.html#index_s"},
                                {text: "t", url: "functions_func_t.html#index_t"},
                                {text: "u", url: "functions_func_u.html#index_u"},
                                {text: "~", url: "functions_func_0x7e.html#index_0x7e"}]
                        },
                        {
                            text: "Variabili", url: "functions_vars.html", children: [
                                {text: "a", url: "functions_vars.html#index_a"},
                                {text: "b", url: "functions_vars.html#index_b"},
                                {text: "c", url: "functions_vars.html#index_c"},
                                {text: "d", url: "functions_vars.html#index_d"},
                                {text: "e", url: "functions_vars.html#index_e"},
                                {text: "f", url: "functions_vars.html#index_f"},
                                {text: "i", url: "functions_vars.html#index_i"},
                                {text: "l", url: "functions_vars.html#index_l"},
                                {text: "m", url: "functions_vars.html#index_m"},
                                {text: "n", url: "functions_vars.html#index_n"},
                                {text: "p", url: "functions_vars.html#index_p"},
                                {text: "r", url: "functions_vars.html#index_r"},
                                {text: "t", url: "functions_vars.html#index_t"},
                                {text: "u", url: "functions_vars.html#index_u"},
                                {text: "y", url: "functions_vars.html#index_y"}]
                        },
                        {text: "Funzioni collegate", url: "functions_rela.html"}]
                }]
        },
        {
            text: "File", url: "files.html", children: [
                {text: "Elenco dei file", url: "files.html"},
                {
                    text: "Elementi dei file", url: "globals.html", children: [
                        {text: "Tutto", url: "globals.html"},
                        {text: "Funzioni", url: "globals_func.html"},
                        {text: "Ridefinizioni di tipo (typedef)", url: "globals_type.html"},
                        {text: "Definizioni", url: "globals_defs.html"}]
                }]
        }]
}
