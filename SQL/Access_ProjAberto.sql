SELECT Projetos.*
FROM Projetos
WHERE ((([Projetos].Status)<>"Concluído" And ([Projetos].Status)<>"Adiado") And ([Projetos].Status<>"Cancelado"))
ORDER BY [Projetos].[Prioridade], [Projetos].[Proprietário], [Projetos].[Data de Término], [Projetos].Status;