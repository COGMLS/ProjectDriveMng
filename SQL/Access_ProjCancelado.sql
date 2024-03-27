SELECT Projetos.*
FROM Projetos
WHERE (([Projetos].Status)="Cancelado")
ORDER BY [Projetos].Status DESC , [Projetos].[Prioridade], [Projetos].[Data de Término] DESC;